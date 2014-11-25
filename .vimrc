set nocompatible
set syntax=on
set noeb
set confirm
set autoindent
set cindent
set tabstop=4
set softtabstop=4
set shiftwidth=4
set noexpandtab
set smarttab
set number
set ignorecase
set incsearch
set enc=utf-8
set fencs=utf-8,ucs-bom,shift-jis,gb18030,gbk,gb2312,cp936
set langmenu=zh_CN.UTF-8
set helplang=cn
set ruler
filetype on
filetype plugin on
filetype indent on
set viminfo+=!
set iskeyword+=_,$,@,%,#,-
set wildmenu
set backspace=2
set whichwrap+=<,>,h,l
set mouse=a
set selection=exclusive
set selectmode=mouse,key
set report=0
set shortmess=atI
set showmatch
set matchtime=5
set scrolloff=3
set smartindent
if has("autocmd")
	autocmd FileType xml,html,tex set ts=2
	autocmd FileType xml,html,tex set softtabstop=2
	autocmd FileType xml,html,tex set sw=2
	autocmd FileType xml,html,c,cs,java,perl,shell,bash,cpp,python,vim,php,ruby set number
	autocmd FileType xml,html vmap <C-o> <ESC>'<i<!--<ESC>o<ESC>'>o-->
	autocmd FileType java,c,cpp,cs vmap <C-o> <ESC>'<o/*<ESC>'>o*/
endif
map <F5> :call CompileRunFile()<CR>
func! CompileRunFile()
	exec "w"
	if &filetype == 'c'
		exec "!gcc -O2 % -o %< -lm -Wall -Wextra"
		exec "!./%<"
	elseif &filetype == 'cpp'
		exec "!g++ -O2 % -o %< -lm -Wall -Wextra"
		exec "!./%<"
	elseif &filetype == 'python'
		exec "!python %"
	elseif &filetype == 'perl'
		exec "!perl %"
	elseif &filetype == 'tex'
		exec "!pdflatex % >/dev/null"
		exec "!evince %<.pdf 2>/dev/null"
	elseif &filetype == 'scheme'
		exec "!scheme --quiet < %"
	elseif &filetype == 'sh'
		exec "!./%"
	elseif &filetype == 'zsh'
		exec "!./%"
	endif
endfunc
map <F6> :call CompileDebugFile()<CR>
func! CompileDebugFile()
	exec "w"
	if &filetype == 'c'
		exec "!gcc -g2 % -o %< -lm -Wall -Wextra"
		exec "!gdb %<"
	elseif &filetype == 'cpp'
		exec "!g++ -g2 % -o %< -lm -Wall -Wextra"
		exec "!gdb %<"
	elseif &filetype == 'tex'
		exec "!pdflatex %"
		exec "!evince %<.pdf 2>/dev/null"
	elseif &filetype == 'scheme'
		exec "!scheme < %"
	endif
endfunc
map <F9> :call RunFile()<CR>
func! RunFile()
	exec "w"
	if &filetype == 'c'
		exec "!./%<"
	elseif &filetype == 'cpp'
		exec "!./%<"
	elseif &filetype == 'tex'
		exec "!evince %<.pdf 2>/dev/null"
	endif
endfunc
map <F12> :%y+<CR>

set foldenable
set foldlevel=20
set foldmethod=indent
nnoremap <space> @=((foldclosed(line('.')) < 0) ? 'zc' : 'zo')<CR>

let g:snips_author='Seter'

set dictionary+=/usr/share/dict/american-english

"set runtimepath+=/home/seter/.vim/bundle/vim-ibus/

let g:paredit_mode = 0
let g:lisp_rainbow = 1
set pastetoggle=<F10>
"autocmd VimLeave * call system("xsel -ib", getreg('+'))
