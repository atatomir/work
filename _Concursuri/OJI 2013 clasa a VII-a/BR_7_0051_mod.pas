var c:array[1..100003]of char;
    a:array[1..100003]of longint;
    n,i,cont,pos1,pos2:longint;
    x:char;
    iesi:boolean;

begin
  assign(input,'compar.in'); reset(input);
  assign(output,'compar.out'); rewrite(output);
  pos1 := 1; pos2 := n-1;

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

                        // calcul stanga-dreapta cu cautare >
    while ((pos1+1) <= (n-1)) and ((c[pos1] <> '>' )or(a[pos1] <>0 )) do inc(pos1);
    if (a[pos1]=0)and(c[pos1]='>') then
    begin
      a[pos1] := cont;
      dec(cont);
      iesi := false;
      inc(pos1);
    end;

    pos2 := n-1;                  // calcul dreapta-stanga cu cautare <
    while ((pos2-1) >= 1) and ((c[pos2] <> '<')or(a[pos2+1] <> 0)) do dec(pos2);
    if (a[pos2+1]=0) and(c[pos2]='<') then
    begin
      a[pos2+1] := cont;
      dec(cont);
      iesi := false;
      inc(pos2);
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
