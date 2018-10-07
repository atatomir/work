set expandtab
set tabstop=4 "dimensiune tab
set shiftwidth=4 "dimesiune autoindent
set autoindent 
set nu "show number line
syntax on
set splitright
set splitbelow

inoremap {  {}<Left>
inoremap (  ()<Left>
inoremap [  []<left>

inoremap <expr> )  strpart(getline('.'), col('.')-1, 1) == ")" ? "\<Right>" : ")"
inoremap <expr> ]  strpart(getline('.'), col('.')-1, 1) == "]" ? "\<Right>" : "]"

map m Ypi    

map <F9>    :w<Enter>:!g++ -std=c++11 -O2 -o exec %<Enter>
map <F10>   :!time ./exec<Enter>
map <F8>    :split test.in<Enter>
map <F7>    :split test.out<Enter>
map <F6>    :!cat % \| pbcopy \| echo "File copied to clipboard"<Enter>
