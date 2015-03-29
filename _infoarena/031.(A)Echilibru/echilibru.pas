var t,ti,n,i,sum,act,rez:longint;
    a:array[1..20]of longint;
    contin,gasit:boolean;

procedure Rezolva(act,util,sumact:longint);
begin
  if contin then
  begin
    if act = 2*n+1 then
    begin
      if (util = n)and(sum div 2 = sumact) then
      begin
        gasit := true;
        contin := false;
      end;
    end
    else
    begin
      Rezolva(act+1,util+1,sumact+a[act]);
      Rezolva(act+1,util,sumact);
    end;

  end;


end;

begin
  assign(input,'echilibru.in'); reset(input);
  assign(output,'echilibru.out'); rewrite(output);

  readln(t);  rez := 0; act := 1; for i := 1 to t-1 do act := act*2;
  for ti := 1 to t do
  begin
    read(n);  sum := 0;
    for i := 1 to 2*n do
    begin
      read(a[i]);
      sum := sum + a[i];
    end;

    readln();   contin := true;  gasit := false;

    if sum mod 2 = 0 then
    begin
      Rezolva(1,0,0);
    end;

    if gasit then rez := rez + act;


    if ti < t then act := act div 2;
  end;

  writeln(rez);

  close(input);
  close(output);
end.
