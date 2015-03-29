var t,ti,n,x,i:longint;
    a:array[1..6]of longint;
    bufin:array[1..65000]of byte;
    ok:boolean;

function verif(x:longint):boolean;
var min:longint;
begin
  min := x div 500; if a[6] < min then min := a[6];
  a[6] := a[6] - min; x := x - 500*min;

  min := x div 100; if a[5] < min then min := a[5];
  a[5] := a[5] - min; x := x - 100*min;

  min := x div 50; if a[4] < min then min := a[4];
  a[4] := a[4] - min; x := x - 50*min;

  min := x div 10; if a[3] < min then min := a[3];
  a[3] := a[3] - min; x := x - 10*min;

  min := x div 5; if a[2] < min then min := a[2];
  a[2] := a[2] - min; x := x - 5*min;

  min := x ; if a[1] < min then min := a[1];
  a[1] := a[1] - min; x := x - min;

  if x > 0 then verif := false else verif := true;


end;

begin
  assign(input,'bancomat.in'); reset(input);
  assign(output,'bancomat.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(t);
  for ti := 1 to t do
  begin
    readln(a[1],a[2],a[3],a[4],a[5],a[6]);
    readln(n);  ok := true;
    for i := 1 to n do
    begin
      read(x);
      if not verif(x) then
      begin
        ok := false;
        break;
      end;
    end; readln();

    if ok then
      writeln('YES')
    else
      writeln('NO');

  end;


  close(input);
  close(output);
end.