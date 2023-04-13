## text editor
### why learn a text editor?
* text editors are more ubiquitous than IDEs
* they are high integrated into the Unix tradition
* editors are designed to work with plain text and are highly optimized to perform associated tasks
 * IDEs are supersets of text editors and evolved from them. A lot of skills associated with text editors can be applied to IDEs
 * they're fun and an enduring part of our culture 
 
### which text editor?

* it doesn't matter, unless you like being cool, then choose Emacs
* pick one and stick to it
* Emacs vs Vim is an enternal war

#### Emacs

* Non-modal interface, key bindings can be supported OS-wide
* Server architecture
* Extensible through a Lisp Variant, Emacs Lisp
* Many beginner friendly variants available ([spaceemacs](https://www.spacemacs.org/),  [doomemacs](https://github.com/doomemacs/doomemacs))
* able to emulate vi
* powerful file manager (dired), integrated debugger, large set of developer tools built in
* "An OS inside an OS": the base install includes two web browsers, several terminal emulators, mail agents, IRC, and video games!
* Unfortunately this has led many critics to descibe Emacs as "bloated", "slow to start", and "using a large amount of memory". 
* Mastering Emacs has a large learning curve and Lisp is difficult to learn

#### Vim
* modal interface
* commands are composable
* Vim loads faster than Emacs and uses less resources 
* High cusomizable through Vim script
* More ubiquitous than Emacs, virtually every Unix-like system ships with a vi variant
* Embedded systems or other resource constrained environments often include vi, but not Emacs

#### the rest
* Atom, Notepad++, Sublime Text, Visual Studio Code
* Most of these are based on Emacs philosophy that it can be modified and extended cleanly
  * Sublime is extended through Python, Atom through Coffeescript
* They generally tend towards Emacs' monolithic, special-purpose commands rather than Vim's composability



### how to learn a text editor 
* Start with a tutorial
  * Emacs has a built in tutorial! just start Emacs and type `C-h t`, ie `Ctrl-h` and then `t`
  * [Vim](https://missing.csail.mit.edu/2020/editors/) also has a built in tutorial! Just start Vim and type `ESC:q!<return>`

* stick with using the editor (even if it slows you down) for all your text editing needs
  1 Watch out for actions you repeat or spend a lot of time on
  2 Find out if there is a command to do it faster
  3 Train using the command until it's muscle memory

* you will likely be more efficient in about ~20 hours
* keep learning! Modern text editors are constantly being extended to be more customizable 

### references 
https://en.wikipedia.org/wiki/Editor_war

https://missing.csail.mit.edu/2020/editors/

https://moolenaar.net/habits.html
  
  
  
