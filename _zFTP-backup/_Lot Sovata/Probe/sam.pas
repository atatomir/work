const modd=1000003;
var n,i,cont,h,nn:Longint;
    c:array[0..100005,1..2]of longint;
    a:array[0..100005]of longint;
    bufin:array[1..65000]of byte;
    sum,sl:int64;

begin
  assign(input,'sam.in'); reset(input);
  assign(output,'sam.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n); nn := n;
  for i := 1 to n do read(a[i]);

  i := 1; cont := 0; sum := 1; h := 0;
  while a[i] > a[i+1] do
  begin
    inc(i);
    inc(h);

    if i > n then begin writeln(nn-1); close(input); close(output); exit;end;
  end;
  if h > 0 then sum := sum*h; sum := sum mod modd;


  inc(i);

  c[0,1] := 0;

  h := 0;
  while a[n] > a[n-1] do
  begin
    inc(h);
    dec(n);

    if n = 0 then begin writeln(nn-1); close(input); close(output); exit;end;
  end;
  if h > 0 then  sum := sum * h; sum := sum mod modd;

  while i < n do
  begin

    c[0,2] := i;

    cont := 0;
    while a[i] <= a[i+1] do
    begin
      inc(cont);
      c[cont,1] := a[i];
      c[cont,2] := i;
      inc(i);

      if i = n then break;
    end;
    inc(cont);
    c[cont,1] := a[i];
    c[cont,2] := i;
    inc(i);


    sl := 0;
    if i < n then
    while a[i] >= a[i+1] do
    begin
      while c[cont,1] > a[i] do dec(cont);
      sl := sl + (i- c[cont,2]);

      inc(i);

      if i = n then break;
    end;

    while c[cont,1] > a[i] do dec(cont);
    sl := sl + (i- c[cont,2]);
    inc(i);

    sl := sl mod modd;
    sum := sum * sl;
    sum := sum mod modd;

  end;

  writeln(sum);

  close(input);
  close(output);
end.
