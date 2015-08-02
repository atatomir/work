var n:longword;
    fo:text;

procedure citire;
var f :text;
begin
  assign(f,'file.in');reset(f);
  read(f,n);
  close(f);
end;

procedure scrie_sus;
var i:longword;
    l,lg,nr:int64;
begin
  nr := 1;
  l:= 1;
  lg:= 2;
  for i := 1 to (n-1) div 2 do
  begin
    nr := nr + 2*l + 2*lg - 5;
    l := l + 2;
    lg:= lg + 2;
  end;
  l := l -2;
  lg := lg-2;
  for i := 1 to (n-1)div 2 do
  begin
    write(fo,nr,' ');
    //writeln(nr,'-',2*l,'-',2*lg,'-',nr-2*l-2*lg-5);
    nr := nr - 2*l - 2*lg + 5;
    lg := lg-2;
    l:= l -2;
  end;
end;

procedure scrie_jos;
var i:longword;
    l,lg,nr:int64;
begin
  l := 2;
  lg:= 3;
  nr := 1 ;
  for i := 1 to (n-1) div 2 do
  begin
    nr := nr + 2*l + 2*lg -5;
    write(fo,nr,' ');
    l := l+2;
    lg:= lg+2;
  end;
end;

procedure scrie_stanga;
var i:longword;
    l,nr:int64;
begin
  nr := 1;
  l:= 3;
  for i := 1 to (n-1) div 2 do
  begin
    nr := nr + 4*l - 5 ;
    l := l + 2;
  end;
  l := l -2;
  for i := 1 to (n-1)div 2 do
  begin
    write(fo,nr,' ');
    //writeln(nr,'-',2*l,'-',2*lg,'-',nr-2*l-2*lg-5);
    nr := nr - 4*l + 5;
    l:= l -2;
  end;
end;

procedure scrie_dreapta;
var i:longword;
    l,nr:int64;
begin
  l := 2;
  nr := 1 ;
  for i := 1 to (n-1) div 2 do
  begin
    nr := nr + 4*l +  -5;
    write(fo,nr,' ');
    l := l+2;
  end;
end;

procedure scrie;
begin
  //writeln(n);
  assign(fo,'file.out'); rewrite(fo);
  write(fo,'Pe coloana principala se afla numerele: ');
  scrie_sus;
  write(fo,'1 ');
  scrie_jos;
  writeln(fo);;
  write(fo,'Pe linia principala se afla numerele: ');
  scrie_stanga;
  write(fo,'1 ');
  scrie_dreapta;
  close(fo);
end;


begin
  citire;
  scrie;
end.
