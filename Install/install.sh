#!/bin/bash

# Use to install appimage in linux
# $1: install or remove
# $2: run

case "$1" in
    remove)
        echo "remove ..."
        rm -f /usr/share/applications/ChineseChess.desktop
        rm -f ~/.config/autostart/ChineseChess.desktop
        rm -f /usr/share/pixmaps/ChineseChess.png
    ;;

    install|*)
        echo "install ..."
        # Install desktop
        if [ -f /usr/share/applications/ChineseChess.desktop ]; then
            rm /usr/share/applications/ChineseChess.desktop
        fi
        ln -s `pwd`/share/applications/ChineseChess.desktop /usr/share/applications/ChineseChess.desktop

        # Install auto run on boot
        if [ ! -d ~/.config/autostart ]; then
            mkdir -p ~/.config/autostart
            chmod a+wr ~/.config/autostart
        fi
        if [ -f ~/.config/autostart/ChineseChess.desktop ]; then
            rm ~/.config/autostart/ChineseChess.desktop
        fi
        ln -s `pwd`/share/applications/ChineseChess.desktop ~/.config/autostart/ChineseChess.desktop

        # Reset exec to desktop
        sed -i "s/Exec=.*//g" `pwd`/share/applications/ChineseChess.desktop
        echo "Exec=`pwd`/ChineseChess-x86_64.AppImage" >> `pwd`/share/applications/ChineseChess.desktop

        # Install applications icon
        if [ -f /usr/share/pixmaps/ChineseChess.png ]; then
            rm /usr/share/pixmaps/ChineseChess.png
        fi
        if [ ! -d /usr/share/pixmaps ]; then
            mkdir -p /usr/share/pixmaps
        fi
        ln -s `pwd`/share/pixmaps/ChineseChess.png /usr/share/pixmaps/ChineseChess.png
        
        # Whether run after install
        if [ "$2" = "run" ]; then
            ./ChineseChess-x86_64.AppImage
        fi
        ;;
esac
