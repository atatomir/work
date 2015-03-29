var x,loc,cauta,h:int64; n,i,j,nr:longint;
guv,gv,min:int64;
    a:array[1..20010]of longint;
    bufin:array[1..65000]of byte;
    sume:array[1..20010]of int64;

begin
  assign(input,'politic.in');  reset(input);
  assign(output,'politic.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n);
  nr := 0;  loc := 1; read(cauta);
  for i := 2 to n do           //citire + realizare sir a
  begin
    inc(cauta);
    read(x);
    if x = cauta then
    begin
      inc(loc);
    end
    else
    begin
      inc(nr);
      a[nr] := loc;
      loc := 1;
      cauta := x;
    end;
  end;


  inc(nr);
  a[nr] := loc;

  writeln(nr);  //scriere nr partide
  min := n div 2;  guv := 0;

  sume[1] := a[1];
  for i := 2 to nr do
    sume[i] := sume[i-1] + a[i];



  j := 1;
  while sume[j]  < min do inc(j);
  guv := guv + nr -j +1;

  h := nr-1;
  for i := 1 to h do
  begin
    gv := guv;
    while (sume[j] - sume[i] <= min)and(j<nr) do inc(j);
    if sume[j]-sume[i] > min then guv := guv + nr - j +1 ;
    if gv = guv then break ;
  end;

  writeln(guv);

  close(input);
  close(output);
end.
