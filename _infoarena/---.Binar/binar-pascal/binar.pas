var n,m,i,j:longint;
    s:ansistring;
    a:array[1..2005]of ansistring;
    bufin,bufout:array[1..65000]of byte;
    cont:array[1..2005]of longint;
    t0,t1:array[1..2005] of longint;
 
procedure Sort(l, r,pas: longint);
var
  i: longint;
  nr0,nr1:longint;
begin
  //writeln(pas);
  //for i := 1 to m do write(cont[i],' ');
  //writeln();
 
  if pas = n + 1 then Exit;
 
  nr0 := 0; nr1 := 0;
 
  for i := l to r do
    if a[pas][cont[i]] = '0' then
    begin
      nr0 := nr0 + 1;
      t0[nr0] := cont[i];
    end
    else
    begin
      nr1 := nr1 + 1;
      t1[nr1] := cont[i];
    end;
 
  for i := 1 to nr0 do
    cont[l+i-1] := t0[i];
  for i := 1 to nr1 do
    cont[l+i-1+nr0] := t1[i];
 
  if nr0 > 0 then Sort(l,l+nr0-1,pas+1);
  if nr1 > 0 then Sort(l+nr0, r,pas+1);
end;
 
 
begin
  assign(input,'binar.in'); reset(input);
  assign(output,'binar.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);
 
  readln(n,m);
  for i := 1 to m do cont[i] := i;
 
 
  for i := 1 to n do
  begin
    readln(a[i]);
 
  end;
 
  Sort(1,m,1);
 
  for i := 1 to m do write(cont[i],' ');
 
  close(input);
  close(output);
end.