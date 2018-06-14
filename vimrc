set expandtab
set tabstop=4
set softtabstop=4
set shiftwidth=4
set autoindent
set textwidth=80 
set nu
syntax on

inoremap {  {}<Left>
inoremap (  ()<Left>
inoremap [  []<left>

inoremap <expr> )  strpart(getline('.'), col('.')-1, 1) == ")" ? "\<Right>" : ")"
inoremap <expr> ]  strpart(getline('.'), col('.')-1, 1) == "]" ? "\<Right>" : "]"

map m Ypi    

map <F9>    :w<Enter>:!g++ -std=c++11 -o exec main.cpp<Enter>
map <F10>   :!./exec<Enter>
map <F8>    :!vim test.in<Enter>
map <F7>    :!vim test.out<Enter>
