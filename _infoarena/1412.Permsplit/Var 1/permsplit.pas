var n,i,j,s,f,t:longint;
    a,r:array[0..1000001]of longint;
    iesi:boolean;

procedure add(x:longint);
begin
  inc(t);
  r[t] := x;
end;

begin
  assign(input,'permsplit.in'); reset(input);
  assign(output,'permsplit.out'); rewrite(output);

  readln(n);
  for i := 1 to n do read(a[i]);

  i := 1 ; j := n; s := 1; f := n; t := 0;
  repeat
    iesi := true;
    if a[i] = s then
    begin
      inc(i);
      inc(s); iesi := false; add(i-1);
    end
    else
    if a[i] = f then
    begin
      inc(i);
      dec(f); iesi := false;  add(i-1);
    end
    else
    if a[j] = s then
    begin
      dec(j);
      inc(s); iesi := false;  add(j);
    end
    else
    if a[j] = f then
    begin
      dec(j);
      dec(f); iesi := false;  add(j);
    end;

    if i=j then iesi := true;

  until iesi = true;


  if i<>j then
    write('-1')
  else
    for i := 1 to t do write(r[i],' ');


  close(input);
  close(output);
end.