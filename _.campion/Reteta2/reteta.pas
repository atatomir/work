var n,m,i,op,t,ti,p:longint;
    pret:array[0..25]of longint; // pret per produs
    conf:array[0..25]of longint; // configuratie reteta
    cost:array[0..25]of real; // cost per reteta
    target:longint;
    cmin:real;
    bufin:array[1..65000]of byte;

procedure Rezolva(pas,config:longint;cloc:real);
begin      //writeln(pas,' ',config,' ',cloc,' ',target);
  if pas = m+1 then
  begin
    if config = target then
      if cmin > cloc then cmin := cloc;
  end
  else
  begin
    Rezolva(pas+1,config,cloc);

    if config and conf[pas] = 0 then
      Rezolva(pas+1,config or conf[pas],cloc+cost[pas]);
  end;
end;

begin
  assign(input,'reteta2.in'); reset(input);
  assign(output,'reteta2.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,m);
  for i := 1 to m do readln();
  for i := 1 to n do read(pret[i]);
  reset(input);
  readln(n,m);

  for i := 1 to m do
  begin
    read(op);
    cost[i] := 0; conf[i] := 0;
    read(t);
    for ti := 1 to t do
    begin
      read(p);
      cost[i] := cost[i] + pret[p];
      conf[i] := conf[i] or (1 shl (p-1))
    end;

    cost[i] := cost[i] / op;

    readln();
  end;

  target := (1 shl n )-1;
  cmin  := 100000;

  Rezolva(1,0,0);

  writeln(cmin:0:1);

  close(input);
  close(output);
end.
