Get-ChildItem -Path "d:\Dev\GitHub\tekisasu\" -Recurse -Include "*.cpp", "*.h" | ForEach-Object {
>>     Select-String -Path $_.FullName -Pattern '\bgodot\b' -AllMatches | 
>>     Select-Object Path, LineNumber, Line
>> } | Out-GridView

Get-ChildItem -Path "d:\Dev\GitHub\tekisasu\" -Recurse -Include "*.cpp", "*.h" | ForEach-Object {
>>     Select-String -Path $_.FullName -Pattern '\bGodot\b' -AllMatches | 
>>     Select-Object Path, LineNumber, Line
>> } | Out-GridView

Get-ChildItem -Path "d:\Dev\GitHub\tekisasu\" -Recurse -Include "*.cpp", "*.h" | ForEach-Object {
>>     Select-String -Path $_.FullName -Pattern '\bGODOT\b' -AllMatches | 
>>     Select-Object Path, LineNumber, Line
>> } | Out-GridView