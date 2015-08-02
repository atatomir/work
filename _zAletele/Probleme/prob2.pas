uses crt;
var n,a1,a2,a,b:int64;
    ln,i:integer;
    e:int64;
    iesi:boolean;

begin
  clrscr;
  write('n= '); readln(n);
  i:= 0;
  iesi:= false;
  repeat
    inc(i);
    if (i*(i+1)) div 2 >= n then
      iesi := true;
  until iesi = true;
  //writeln(i);
  a2 := (i*(i+1))div 2;
  a1 := (i*(i-1))div 2+1;
  b := n-a1+1;
  a:= a2-n+1 ;
  write('A',a,' B',b);
  read(a);
end.