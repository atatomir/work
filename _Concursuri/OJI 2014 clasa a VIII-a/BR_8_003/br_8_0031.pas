var a:array[1..500,1..500]of byte;
    n,m,i,j,op,cont:longint;
    si,sj:longint;
    bufin:array[1..65000]of byte;


procedure Rez_1;
var i,j,p:longint;
    iesi:boolean;
begin
  i := si; j := sj; p := 1; iesi := false;

  repeat
    case a[i,j] of
      1: inc(j);
      2: dec(i);
      3: dec(j);
      4: inc(i);
    end;

    if (1<=i)and(1<=j)and(i<=n)and(j<=m)and((i<>si)or(j<>sj)) then
      inc(p)
    else
      iesi := true;

  until iesi;

  writeln(p,'000');

end;


begin
  assign(input,'arrows.in'); reset(input);
  assign(output,'arrows.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(op);
  readln(n,m);
  for i := 1 to n do
  begin
    for j := 1 to m do
    begin
      read(a[i,j]);
    end;
    readln();
  end;
  readln(si,sj);

  case op of
    1: Rez_1;
    2: writeln(n*m);
    3: Rez_1;
  end;



  close(input);
  close(output);
end.
