## Snazzy Powerline Style Terminal Prompt

![Screen Shot](documentation/ScreenShot.png)


This repository contains my snazzy [Powerline](https://powerline.readthedocs.io/en/latest/index.html) style terminal prompt

**Options Environment Variable:**. 
SNAZZY\_PROMPT=<Segment Name>,Foreground color,Background color[,Alternate Foreground color,Alternate Background color];<next segment spec>

Segment Names:
*  *cwd* Current working directory
*  *error* Error status of the last command
*  *git* git status if the current directory is a git working tree
*  *machine* machine/host name
*  *user* user name

```zsh
#*****************************************************************************************
# prompt setup
#*****************************************************************************************
 export SNAZZY_PROMPT="cwd,235,179,235,166;git,235,219,235,40;error,235,166"

snazzy_prompt_precmd() {
       PS1="$(/usr/local/bin/SnazzyPrompt --error $?)"
}

install_snazzy_prompt_precmd() {
  for s in "${precmd_functions[@]}"; do
    if [ "$s" = "snazzy_prompt_precmd" ]; then
      return
    fi
  done
  precmd_functions+=(snazzy_prompt_precmd)
}
install_snazzy_prompt_precmd  
...  
```
  
# Building SnazzyPrompt  
cd scripts
./build-libgit2.sh
open the Xcode project file and build