const mod1= 9001;

var n,i,j,m,t:longint;
    a:array[1..5001,1..3]of smallint;
    s:longint;

begin
  assign(input,'flori.in'); reset(input);
  assign(output,'flori.out'); rewrite(output);

  read(n);


  m := (n + 1) div 2;

  for i := 2 to m do
  begin
    a[i,1] := 0;
    a[i,2] := 0;
  end;

  for i := 3 to n do
  begin
    a[1,1] := i-2; a[1,2] := i-1; a[1,3] := i ;

    t := (i+1) div 2;
    for j := 2 to t do
    begin
      a[j,3] := (a[j,2] + a[j-1,1])  mod mod1;
    end;
    inc(t);
    for j := t to m do a[j,3] := 0;

    for j := 2 to m do
    begin
      a[j,1] := a[j,2];
      a[j,2] := a[j,3];
    end;

  end;

  s := 0;

  for i := 1 to m do s := (s+ a[i,3]) mod mod1;

  writeln(s);

  //for i := 1 to m do writeln(a[i,1],' ',a[i,2],' ',a[i,3]);

  close(input);
  close(output);
end.
