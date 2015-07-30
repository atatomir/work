var n,c,i,rft,crt,h1,h2,h3:longint;
    bufin:array[1..65000]of byte;
    a,r:array[0..10010]of longint;

function max2(a,b:longint):longint;
begin
  max2 := a;
  if b > a then max2 := b;
end;
function max3(a,b,c:longint):longint;
begin
  max3 := a;
  if b > a then max3 := b;
  if c > max3 then max3 := c;
end;

begin
  assign(input,'rafturi.in'); reset(input);
  assign(output,'rafturi.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,c);
  for i := 0 to n+2 do a[i] := 0;

  for i := 1 to c do
  begin
    readln(rft,crt);
    if a[rft] < crt then a[rft] := crt;
  end;

  r[0] := 0;
  r[1] := a[1];
  r[2] := max2(a[1],a[2]);

  for i := 3 to n do
  begin
    h1 := max3(a[i],a[i-1],a[i-2]) + r[i-3];
    h2 := max2(a[i],a[i-1]) + r[i-2];
    h3 := r[i-1] + a[i];

    if h2 < h1 then h1 := h2;
    if h3 < h1 then h1 := h3;
    r[i] := h1;
  end;

  writeln(r[n]);


  close(input);
  close(output);
end.