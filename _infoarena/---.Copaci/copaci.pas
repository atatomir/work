type point=record
       x,y:int64;
     end;
var n,i:longint;
    a:array[0..100005]of point;
    bufin:array[1..65000]of byte;
    int,aria,ext:int64;

function cmmdc(a,b:int64):int64;
var t:int64;
begin
  if a < 0 then a := -a;
  if b < 0 then b := -b;
  if a < b then
  begin
    t := a; a := b; b := t;
  end;
  while b <> 0 do
  begin
    a := a mod b;
    t := a; a := b; b := t;
  end;
  cmmdc := a;
end;

begin
  assign(input,'copaci.in'); reset(input);
  assign(output,'copaci.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n);
  for i := 1 to n do readln(a[i].x,a[i].y);
  a[n+1].x := a[1].x; a[n+1].y := a[1].y;

  aria := 0; ext := 0;
  for i := 1 to n do
  begin
    aria := aria + a[i].x*a[i+1].y-a[i+1].x*a[i].y;
    ext := ext + cmmdc(a[i].x-a[i+1].x,a[i].y-a[i+1].y);
  end;

  if aria < 0 then aria := -aria;

  int := aria + 2 - ext;
  writeln(int div 2);

  close(input);
  close(output);
end.