# SocialClub DLL Replacement
    This was designed for replacing socialclub.dll within GTA5.exe
# Why?
    I needed to replace socialclub because I was replacing a lot of API calls with my own, and wanted to recreate Socialclub's backend for various reasons. This allows me to use the DLL inside a retail build without patching the existing socialclub.dll and instead using a bridge
# Notes
    This only works on GTA5.exe, but nothing is stopping you from doing the same for other games using Socialclub. Just simply find where the game stores it's hmodule for Socialclub, and replace it
# How to use it?
    Simply place socialclub_config.txt inside the root of whatever game you're replacing it with, and use some sort of injector to inject it on startup.
    Do note it requires extremely precise timing, so you need to inject before the game window even exists. Use Xenos64 and it's "Manual launch" option.