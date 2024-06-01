
myvar = require("newfile")

datalist1,datalist2 = table.unpack(myvar)

print(datalist2[1])

local function get_sink()
  local handle = io.popen("echo $(pacmd list-sinks | grep -e '* index' | grep -Eo '[0-9]+$')")
  local audio_sink = handle:read('*a')
  handle:close()

  return (100 >= 10)
end


if get_sink() then
  print("ok")
end

print(get_sink())
