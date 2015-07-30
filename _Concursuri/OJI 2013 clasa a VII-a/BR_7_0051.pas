var c:array[1..100003]of char;
    a:array[1..100003]of longint;
    n,i,cont:longint;
    x:char;
    iesi:boolean;

begin
  assign(input,'compar.in'); reset(input);
  assign(output,'compar.out'); rewrite(output);

  n := 0;
  while not eof(input)do     //citire
  begin
    read(x);
    case x of
      '<':begin inc(n); c[n] := '<'; end;
      '>':begin inc(n); c[n] := '>'; end;
    end;
  end;

  inc(n);
  writeln(n);                 //scriere n
  for i := 1 to n do a[i] := 0;

  cont := n;

  repeat
    iesi := true;

    i := 1;                         // calcul stanga-dreapta cu cautare >
    while ((i+1) <= (n-1)) and ((c[i] <> '>' )or(a[i] <>0 )) do inc(i);
    if (a[i]=0)and(c[i]='>') then
    begin
      a[i] := cont;
      dec(cont);
      iesi := false;
    end;

    i := n-1;                       // calcul dreapta-stanga cu cautare <
    while ((i-1) >= 1) and ((c[i] <> '<')or(a[i+1] <> 0)) do dec(i);
    if (a[i+1]=0) and(c[i]='<') then
    begin
      a[i+1] := cont;
      dec(cont);
      iesi := false;
    end;

  until iesi = true;

  for i := 1 to n+1 do         //umplere restul vectorului
    if a[i] = 0 then
    begin
      a[i] := cont;
      dec(cont);
    end;

  for i := 1 to n do write(a[i],' ');

  close(input);
  close(output);
end.
