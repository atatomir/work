var n,i,t:longint;
    a,r:array[0..1000001]of longint;
    iesi:boolean;

function modulo(x:longint):longint;
begin
  if x < 0 then x := -x;
  modulo := x;
end;

procedure add(x:longint);
begin
  inc(t);
  r[t] := x;
end;

procedure incearca(i:longint);
var j,min,max,h:longint;
    terminat:boolean;
begin
  r[1] := i;
  j := i+1; t := 1;
  if a[i] < a[j] then
  begin
    min := a[i];
    max := a[j];
  end
  else
  begin
    min := a[j];
    max := a[i];
  end;


  repeat   //writeln(i,' ! ',j,' ',r[t]);
    terminat := true;
    if a[i-1] = min - 1 then
    begin
      dec(i);
      dec(min);
      add(i);
      terminat := false;
    end
    else
    if a[i-1] = max + 1 then
    begin
      dec(i);
      inc(max);
      add(i);
      terminat := false;
    end
    else
    if a[j+1] = min - 1 then
    begin
      inc(j);
      dec(min);
      add(j-1);
      terminat := false;
    end
    else
    if a[j+1] = max + 1 then
    begin
      inc(j);
      inc(max);
      add(j-1);
      terminat := false;
    end;

    if j-i = n-1 then terminat := true;

  until terminat ;

  if j-i = n-1 then
  begin
    iesi := true;
    for h := n-1 downto 1 do write(r[h],' ');
  end;

end;

begin
  assign(input,'permsplit.in'); reset(input);
  assign(output,'permsplit.out'); rewrite(output);

  readln(n);
  for i := 1 to n do read(a[i]);
  a[0] := -17; a[n+1] := -17;

  iesi := false;
  for i := 1 to n-1 do
  begin
    if modulo(a[i]-a[i+1]) = 1 then
    begin
      incearca(i);
    end;
    if iesi = true then break;
  end;

  if iesi = false then write('-1');

  close(input);
  close(output);
end.
