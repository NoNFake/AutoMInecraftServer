<h1>Auto Script Minecraft Server</h1>

<h2>-F*ck, really on C++?</h2>
-Yes, I know what I can write on BASH. Why not?
....


<h1>How to build on Linux</h1>
How to build on F*cking Penguin?

```g++ -o myServer mian.cpp -lstdc++fs -Idependencies/include```


<h2>Code for brush</h2>

```bash
#!/bin/bash

RED_COLOR="\033[1;31m"
GREEN_COLOR="\033[1;32m"
YELLOW_COLOR="\033[1;33m"
BLUE_COLOR="\033[1;34m"
MAGENTA_COLOR="\033[1;35m"
CYAN_COLOR="\033[1;36m"
RESET_COLOR="\033[0m"

logo() {
    echo -e "${MAGENTA_COLOR}\tSTArT-ErSerVer${RESET_COLOR}"
}

settings() {
    read -p "${GREEN_COLOR}1. The maximum amount of memory (Xmx): " Xmx
    read -p "2. Initial memory size (Xms): " Xms
    read -p "3. With gui? true | false: " gui

    settingsJson="{\"Xmx\": $Xmx, \"Xms\": $Xms, \"gui\": $gui}"
    echo $settingsJson | jq . > settings.json

    echo "Settings saved to settings.json"
}

first_start() {
    ip_address=$(curl -s https://api64.ipify.org?format=json | grep -oP '\"ip\"\s*:\s*\"\K[^\"]+')
    sed -i.orig "s/server-ip=/server-ip=${ip_address}/g" server.properties

    java -Xms1024M -Xmx1024M -jar *.jar nogui
    sed -i.orig 's/eula=false/eula=true/g' eula.txt
    sed -i.orig 's/online-mode=true/online-mode=false/g' server.properties
}

start() {
    objson=$(cat settings.json)
    Xms=$(echo $objson | jq -r .Xms)
    Xmx=$(echo $objson | jq -r .Xmx)
    gui=$(echo $objson | jq -r .gui)

    if [ "$gui" = "true" ]; then
        command="java -Xms${Xms}M -Xmx${Xmx}M -jar *.jar gui"
    else
        command="java -Xms${Xms}M -Xmx${Xmx}M -jar *.jar nogui"
    fi

    $command
}

check() {
    if [ -e "startup.txt" ]; then
        value=$(<startup.txt)
        if [ "$value" -eq 0 ]; then
            echo -e "${CYAN_COLOR}Is this your first run?${RESET_COLOR}"
            echo 1 > startup.txt
            settings
            first_start
            check
        else
            echo "Starting serv"
            start
        fi
    else
        echo -e "${RED_COLOR}\nFile could not be found.${CYAN_COLOR} Is this your first run?${RESET_COLOR}"
    fi
}


main() {
    logo
    check
    start
}

main
```
