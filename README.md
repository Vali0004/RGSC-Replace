## SocialClub DLL Replacement

This project's purpose is to replace socialclub.dll within games that use it

### Why?
I needed to replace socialclub because I was replacing many API calls with my own and wanted to recreate Socialclub's backend for various reasons. This allows me to use the DLL inside a retail build without patching the existing socialclub.dll, instead using a bridge.

### Notes
This currently only works on GTA5.exe, but the concept can be applied to other games using Socialclub. To adapt it, find where the game stores its hmodule for Socialclub and replace it accordingly.

### How to Use
1. Place `socialclub_config.txt` in the root directory of the game you're targeting.
2. Use an injector to inject the DLL on game startup.
   * Note: Precise timing is crucial. Inject before the game window appears. Xenos64's "Manual launch" option is recommended.
