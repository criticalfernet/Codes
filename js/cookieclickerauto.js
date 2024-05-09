function automate(){
    Game.prefs.particles = 0
    setInterval(()=>{
        Game.ClickCookie()
        Game.autoclickerDetected = 0
    },20)

    let dragonUpdates = [Game.Upgrades['Dragon teddy bear'],Game.Upgrades['Dragon claw'],
                        Game.Upgrades['Dragon fang'],Game.Upgrades['Dragon scale']]
    let unlockedlist = []
    pettime = 10000
    setTimeout(function myFunction(){
        if(unlockedlist.length === dragonUpdates.length) return
        if(Game.PrestigeUpgrades[83].bought == 1 && Game.dragonLevel >= 8) {
            pettime = 50
        if(Game.specialTab !='dragon') Game.specialTab = 'dragon'
        Game.ClickSpecialPic()
        if (dragonUpdates.filter(itm=> itm.unlocked == 1).length != unlockedlist.length){
            unlockedlist = dragonUpdates.filter(itm=> itm.unlocked == 1)
            pettime = 15 * 60 * 1000
        }
        }
        setTimeout(myFunction, pettime)
    },1000)

    setInterval(()=>{

    if(Game.season === 'christmas' && Game.santaLevel < 14){
        Game.UpgradeSanta()
    }
    if(Game.Upgrades["A crumbly egg"].bought == 1 && Game.dragonLevel < 27){
        Game.UpgradeDragon()
    }
    if(Game.dragonLevel == 27 && (Game.dragonAura == 0 || Game.dragonAura2 == 0)){
        if(!Game.dragonAura){
            Game.SetDragonAura(15,0)
            document.getElementById("promptOption0").click()
        }
        if(!Game.dragonAura2){
            Game.SetDragonAura(10,1)
            document.getElementById("promptOption0").click()
        }
    }

    if (Game.Upgrades['Festive biscuit'].unlocked && Game.season !== 'christmas' &&
        ((Game.cookiesPs + 50*Game.computedMouseCps) * 20) + Game.cookies >= Game.Upgrades['Festive biscuit'].basePrice)
    {
        if(Game.Upgrades['Festive biscuit'].canBuy()){
            Game.Upgrades['Festive biscuit'].buy() 
        }else{
            return
        }
    }

    Game.UpgradesInStore.filter(obj=>obj.pool!="toggle").forEach(obj=>{
        if(obj.canBuy() && obj.id !== 69) obj.buy()
        if(obj.canBuy() && obj.id === 69) {Game.UpgradesById[69].buy(1);Game.ClosePrompt();}
    })
    
    // Game.ObjectsById.filter(obj=> !obj.locked).reverse().every(obj=>
    // {
    //     while (Game.cookies >= obj.bulkPrice) obj.buy()
    //     if(obj.amount == 0 && ((Game.cookiesPs + 50*Game.computedMouseCps) * 10) + Game.cookies >= obj.bulkPrice){
    //         return false
    //     }
    //     return true
    // }) 
    TOTALBUILDINGS = Game.ObjectsById.length
    unlockedupg = Game.ObjectsById.filter(obj=> !obj.locked)
    getBiasedIndex = function(){    
        buildingcps = unlockedupg.map(obj=>(obj.storedCps/obj.bulkPrice))
        MaxIndex = buildingcps.indexOf(Math.max(...buildingcps))

        rnd = Math.random()*(unlockedupg.length-1)
        mix = Math.random()

        I = Math.round(rnd * (1-mix) + ((3*MaxIndex+5*(unlockedupg.length-1))/8)*mix)
        console.log(I)
        return I
    }
    build = unlockedupg[getBiasedIndex()]
    while (Game.cookies >= build.bulkPrice) build.buy()
    

    },10000)

    setInterval(()=>{
        prevArray = []
        newArray = Game.PrestigeUpgrades.
            filter(upg => !upg.dname.startsWith("Permanent upgrade")&&upg.bought==0 && upg.parents?.every(par=>par.bought != 0))
            .sort((a, b) => {return a.basePrice - b.basePrice})
        reqPrice = newArray.reduce(
          (accumulator, val,index) => {if(index<4){return accumulator + val.basePrice}}, 0
        );  
        function heavenlyupg(){
            newArray.forEach(upg => upg.buy())
            prevArray = [...newArray]
            newArray = Game.PrestigeUpgrades.
            filter(upg => !upg.dname.startsWith("Permanent upgrade")&&upg.bought==0 && upg.parents?.every(par=>par.bought != 0))
                .sort((a, b) => {return a.basePrice - b.basePrice})
            if(prevArray.length === newArray.length && prevArray.every((val, i) => val === newArray[i])) 
                {setTimeout(()=>{Game.Reincarnate(1); return},1000)}
            else{setTimeout(heavenlyupg,2*1000)}
        }
        if(Game.ascendMeterLevel + Game.heavenlyChips >= reqPrice){
            Game.Ascend(1)
            Game.PrestigeUpgrades.filter(itm=>itm.id == 363)[0].buy()
            Game.PrestigeUpgrades.filter(itm=>itm.id == 363)[0].bought = 1
            setTimeout(heavenlyupg,2*1000)
        }
    },1000*3600*6)

    setInterval(()=>{
        Game.shimmers.forEach(shm => shm.pop())
        if(Game.wrinklers.filter(wrk=>wrk.phase > 1).length > 0){
            Game.wrinklers.filter(wrk=>wrk.phase > 1).forEach(wrk=>wrk.hp = 0)
        }
        if (Game.TickerEffect && Game.TickerEffect.type=='fortune') {
            Game.tickerL.click();
        }
    },1000)
}



/* 

Variables:
  min = 0
  max = 100
  bias = 67      (N)
  influence = 1  (D) [0.0, 1.0]

Formula:
  rnd = random() x (max - min) + min
  mix = random() x influence
  value = rnd x (1 - mix) + bias x mix

    TOTALBUILDINGS = Game.ObjectsById.length
    rnd = Math.random()*20
    mix = Math.random()

    unlockedupg = Game.ObjectsById.filter(obj=> !obj.locked)
    buildingcps = unlockedupg.map(obj=>Math.round(obj.amount * obj.storedCps))
    MaxIndex = buildingcps.findIndex(Math.max(...buildingcps))

    I = Math.floor(rnd * (1-mix) + MaxIndex*mix)
    while (Game.cookies >= unlockedupg[].bulkPrice) obj.buy()
*/