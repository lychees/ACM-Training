%% 信息学奥林匹克中国国家队候选队员论文模板
%% 模板作者：胡伟栋
%% 模板修改：余林韵
%%
\NeedsTeXFormat{LaTeX2e}[1999/12/01]
\ProvidesClass{noithesis}
[2013/02/16 1.0 Template for NOI Thesis]
\LoadClass[12pt, a4paper]{article}
\RequirePackage{enumerate}
\RequirePackage{graphicx,subfigure}
\RequirePackage{amsmath,amsthm,amsfonts,amssymb,bm}
\RequirePackage{txfonts}
\RequirePackage{CJKutf8,ctexutf8}
\RequirePackage{longtable,multirow}
\RequirePackage{color,xcolor}
\RequirePackage{courier}
\RequirePackage{ifthen}
\RequirePackage{calc}
\RequirePackage{ifpdf}
\RequirePackage{titling}
\RequirePackage{listings}
\RequirePackage{fancyhdr}
\RequirePackage{algorithm,algorithmic}
\RequirePackage{booktabs}
\RequirePackage{ulem}

%% 页边距
\setlength{\textwidth}{\paperwidth}
\setlength{\textheight}{\paperheight}
\setlength\marginparwidth{0cm}
\setlength\marginparsep{0cm}
\addtolength{\textwidth}{-6.4cm}
\setlength{\oddsidemargin}{3.2cm-1in}
\setlength{\evensidemargin}{\oddsidemargin}
\setlength{\headheight}{20pt}
\setlength{\topskip}{0pt}
\setlength{\skip\footins}{15pt}
\setlength{\topmargin}{2.8cm-1in}
\setlength{\footskip}{1.5cm}
\setlength{\headsep}{0.5cm}
\addtolength{\textheight}{-8.6cm}

%% 页眉页脚
\pagestyle{fancy}
\renewcommand{\headheight}{20pt}
\renewcommand{\headrulewidth}{0.2pt}
\renewcommand{\footrulewidth}{0pt}
\lhead{\parbox{\textwidth}{\textsf{\footnotesize \thetitle}}}
\chead{}
\rhead{\parbox{\textwidth}{\raggedleft\textsf{\footnotesize \theauthor}}}
\lfoot{\parbox{\textwidth}{\textsf{\footnotesize 2015年信息学奥林匹克中国国家队候选队员论文}}}
\cfoot{}
\rfoot{\parbox{\textwidth}{\raggedleft\footnotesize \thepage{}}}

%% 字体
\newcommand{\song}{\CJKfamily{song}}    % 宋体
\def\songti{\song}
\newcommand{\fs}{\CJKfamily{fs}}        % 仿宋体
\def\fangsong{\fs}
\newcommand{\kai}{\CJKfamily{kai}}      % 楷体
\def\kaishu{\kai}
\newcommand{\hei}{\CJKfamily{hei}}      % 黑体
\def\heiti{\hei}
\newcommand{\li}{\CJKfamily{li}}        % 隶书
\def\lishu{\li}
\newcommand{\you}{\CJKfamily{you}}      % 幼圆
\def\youyuan{\you}

%% 字号
\newlength\noilinespace
\newcommand{\noiChooseFont}[2]{
   \setlength{\noilinespace}{#2*\real{#1}}
   \fontsize{#2}{\noilinespace}\selectfont}
\def\noiDefineFontsize#1#2{
  \expandafter\newcommand\csname #1\endcsname[1][\baselinestretch]{
    \noiChooseFont{##1}{#2}}}
\noiDefineFontsize{chuhao}{42bp}
\noiDefineFontsize{xiaochu}{36bp}
\noiDefineFontsize{yihao}{26bp}
\noiDefineFontsize{xiaoyi}{24bp}
\noiDefineFontsize{erhao}{22bp}
\noiDefineFontsize{xiaoer}{18bp}
\noiDefineFontsize{sanhao}{16bp}
\noiDefineFontsize{xiaosan}{15bp}
\noiDefineFontsize{sihao}{14bp}
\noiDefineFontsize{banxiaosi}{13bp}
\noiDefineFontsize{xiaosi}{12bp}
\noiDefineFontsize{dawu}{11bp}
\noiDefineFontsize{wuhao}{10.5bp}
\noiDefineFontsize{xiaowu}{9bp}
\noiDefineFontsize{liuhao}{7.5bp}
\noiDefineFontsize{xiaoliu}{6.5bp}
\noiDefineFontsize{qihao}{5.5bp}
\noiDefineFontsize{bahao}{5bp}

\renewcommand{\maketitle} {
 \null
 \vskip 2em
\begin{center}
{\xiaoer \bf \@title \par} \vskip 1em {\@author\par}
\end{center}
 \vskip 1em
}

\renewenvironment{abstract}{
\section*{摘~~要}
\kai
}{}

\renewcommand\tableofcontents{%
  \section*{目~~录}
  \@starttoc{toc}\normalsize}

\renewcommand\section{\@startsection{section}{1}{\z@}%
                     {-24bp \@plus -1ex \@minus -.2ex}%
                     {6bp \@plus .2ex}%
                     {\hei \sihao[1.429]}}
\renewcommand\subsection{\@startsection{subsection}{2}{\z@}%
                        {-16bp \@plus -1ex \@minus -.2ex}%
                        {6bp \@plus .2ex}%
                        {\hei\banxiaosi[1.538]}}
\renewcommand\subsubsection{\@startsection{subsubsection}{3}{\z@}%
                           {-16bp \@plus -1ex \@minus -.2ex}%
                           {6bp \@plus .2ex}%
                           {\hei \xiaosi[1.667]}}

\if 0

\fi
