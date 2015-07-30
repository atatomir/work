var max:longint;
    n,cont,i:longint;
    a:array[0..50005]of longint;

function verif(x:longint):boolean;
begin
  if ((a[x-1] < a[x])and(a[x] > a[x+1]))or
     ((a[x-1] > a[x])and(a[x] < a[x+1]))
  then verif := true else verif := false;

  if (x=1)or(x=n) then verif := false;
end;

procedure start(i:longint);
begin
  inc(i); cont := 0;
  while verif(i) do begin inc(i); inc(cont); end;
  if cont > max then max := cont;
  if i < n then start(i);
end;

begin
  readln(n);

  max := 0;
  for i := 1 to n do read(a[i]);

  start(1);

  writeln(max);
end.
