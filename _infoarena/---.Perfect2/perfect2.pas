var op,n,i,cont:longint;
    xmin,xmax,ymin,ymax,y,x,t:int64;

function cmmdc(a,b:longint):longint;
begin
  if a < 0 then a := -a;
  if b < 0 then b := -b;
  if a < b then
  begin
    t := a; a := b ; b := t;
  end;
  while b <> 0 do
  begin
    a := a mod b;
    t := a; a := b ; b := t;
  end;
  cmmdc := a;
end;

begin
  assign(input,'perfect2.in'); reset(input);
  assign(output,'perfect2.out'); rewrite(output);

  readln(op); readln(n);
  if op = 1 then
  begin
    readln(xmin,ymin);
    xmax := xmin; ymax := ymin;
    for i := 2 to n do
    begin
      readln(x,y);
      if x < xmin then xmin := x;
      if x > xmax then xmax := x;
      if y < ymin then ymin := y;
      if y > ymax then ymax := y;
    end;
    writeln(xmin,' ',ymin,' ',xmax,' ',ymax);
  end
  else
  begin
    readln(xmin,ymin); cont := 0;
    for i := 2 to n do
    begin
      readln(x,y);
      if cmmdc(xmin-x,ymin-y) = 1 then inc(cont);
    end;
    writeln(cont);
  end;


  close(input);
  close(output);
end.
