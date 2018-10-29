@echo off
java -Xms1G -Xmx1G -XX:+UseConcMarkSweepGC -classpath sc-mqtt.jar;spigot-1.13.1.jar org.bukkit.craftbukkit.Main
pause