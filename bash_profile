# if running bash
if [ -n "$BASH_VERSION" ]; then
    # include .bashrc if it exists
    if [ -f "$HOME/.bashrc" ]; then
	. "$HOME/.bashrc"
    fi
fi

# set PATH so it includes user's private bin if it exists
if [ -d "$HOME/bin" ] ; then
    PATH="$HOME/bin:$PATH"
fi

if [ -f ~/.ssh-agent ] ; then
   source ~/.ssh-agent
fi

if [ -n "$SSH_AUTH_SOCK" ] ; then
   if [ ! -S $SSH_AUTH_SOCK ] ; then
      ssh-agent -s > ~/.ssh-agent
      source ~/.ssh-agent
      ssh-add
   fi
else
   ssh-agent -s > ~/.ssh-agent
   source ~/.ssh-agent
   ssh-add
fi

