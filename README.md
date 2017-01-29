# QuicDone
Do what you want quickly!

### The commands:
    HK.closeMonitor()   - 关闭显示器  
    HK.quit()           - 退出程序  
    HK.message(text)    - 弹出提示框  
    HK.exec(cmd, param) - 执行程序/命令  
    HK.shell(cmd)       - 执行cmd命令  
    HK.version()        - 显示程序版本号  

### QuicDone.config usage:
```json
{
    "log": true, // Output log file or not.
    "The key what you want to handle.": "The script with javascript. You could just give a path to point to a js file."
}
```

### Here is a example:
```json
{
    "log": true,
    "WIN + C": "HK.exec(\"calc\")",
    "WIN + N": "HK.exec(\"notepad\")",
    "ALT + CTRL + M": "HK.closeMonitor()",
    "ALT + CTRL + O": "HK.message(\"西子，哦嗨哟~~\")",
    "ALT + CTRL + SHIFT + V": "HK.version()",
    "ALT + CTRL + SHIFT + WIN + ESC": "HK.quit()"
}
```