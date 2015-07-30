var n,i,min,rez,x,t:longint;
    bufin:array[1..65000]of byte;
    a:array[1..2,1..2]of longint;

function minim(a,b:longint):longint;
begin
  if a < b then minim := a else minim := b;
end;

begin
  assign(input,'pachete.in'); reset(input);
  assign(output,'pachete.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n); rez := 0;
  readln(a[2,1],a[2,2]);
  min := a[2,2];

  for i := 2 to n do
  begin
    a[1,1] := a[2,1];
    readln(a[2,1],a[2,2]);
    if a[1,1] > a[2,2] then
      rez := rez + a[1,1]-a[2,2]
    else
    begin
      x := a[2,2]- a[1,1];
      t := minim(x,rez);
      rez := rez - t; x := x- t;
      min := min + x;
    end;
  end;

  write(min);

  close(input);
  close(output);
end.
