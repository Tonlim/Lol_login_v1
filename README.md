# Bunch of League of Legends scripts

Dependencies: Visual Studio 2013 (aka I know it will work on that)

##Log in 
- build "generate_password_hash" and "Lol_login_v1"
- put the .exe's (found in /Release/) and "systemvariables_login.txt" together in one folder
- run generate_password_hash.exe to make a password file ("pass.txt")
- run Lol_login_v1.exe

##Invite (normal draft)
- build "invite_normal_draft"
- put the .exe (found in /Release/), "systemvariables_invite_normal_draft.txt" and "invite_normal_draft_names.txt" together in one folder
- make sure your LoL is open, in the default position and the "Start" button is avialable
- run invite_normal_draft.exe


###Note on .txt files and "resource_examples"
All .txt files mentioned here are different for each user. They largely depend on your screen resolution and how Windows opens LoL on your system. I've provided a few examples in resource_examples that work on my machine (---tonlim) and on the machine of a friend (---elite_cart).  
Feel free to try those before making your own.

###Note on "Build"
This folder contains compiled versions of the scripts in this repository. If you don't have access to VS2013 you can try these. Of course you won't be able to debug/finetune the needed .txt files.
