var n,i,max:longint;
    a,v:array[-5..100005]of longint;
    bufin:array[1..65000]of byte;

procedure Rezolva(l,h:longint);
var i,v1,v2:longint;
begin
  v[l] := 0; v[l+1] := 0;
  for i := l+2 to h do
  begin
    v1 := v[i-1];
    v2 := v[i-3] + a[i-1] + a[i-2];
    if v1 > v2 then v[i] := v1 else v[i] := v2;
  end;

  if v[h] > max then max := v[h]
end;

begin
  assign(input,'oo.in'); reset(input);
  assign(output,'oo.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n);
  for i := 1 to n do read(a[i]);
  for i := 1 to 2 do a[n+i] := a[i];

  if n = 2 then
    writeln(a[1]+a[2])
  else
  begin
    max := -1;
    Rezolva(1,n);
    Rezolva(2,n+1);
    Rezolva(3,n+2);

    writeln(max);
  end;


  close(input);
  close(output);
end.
