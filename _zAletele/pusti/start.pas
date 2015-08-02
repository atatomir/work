 var a,b:array [1..1001] of integer;
     n,m,i:integer;
     c:array [1..2002] of integer;
     f:text;
     x:boolean;
     y:integer;
     s:longint;
 begin
 assign(f,'file.bin');
 reset(f);
 read(f,n);
 readln(f,m);
 for i := 1 to n do
 read(f,a[i]);
 readln();
 for i:= 1 to m do
 read (f,b[i]);
 for i:= 1 to n do
 c[i] := a[i];
 for i:= 1 to m do
 c[i+n] := b[i];

 repeat
 x:= false;
 for i := 1 to m+n-1 do
 begin
 if c[i]<c[i+1] then
 begin
 x := true;
 y := c[i];
 c[i] := c[i+1];
 c[i+1] := y;
 end;
 end;


 until x = false;
s := 0;

 for i := 1 to n do
 s:= s+ c[i];

 write('SUMA totala este : ');
 write(s);




close(f);
readln();
 end.
