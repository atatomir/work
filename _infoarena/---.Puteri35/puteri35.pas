var t,ti,t1,t2,i,l1,l2:longint;
    r3,r5:array[1..30]of int64;
    a,b:array[1..30]of byte;
    sum1,sum2,sum,last3,last5:int64;
    bufout:array[1..65000]of byte;

function next3:int64;
var i,rez:longint;
begin
  inc(t1); if t1 > t then begin next3 := 0; exit; end;

  next3 := last3;

  rez := 1;
  for i := 1 to l1+1 do
  begin
    a[i] := a[i] + rez; rez := 0;
    if a[i] = 2 then
    begin
      a[i] := 0;
      rez := 1;
    end;

    if a[i] = 1 then
      next3 := next3 + r3[i]
    else
      next3 := next3 - r3[i];

    if rez = 0 then break;
  end;

  if a[l1+1] = 1 then inc(l1);

  last3 := next3;
end;

function next5:int64;
var i,rez:longint;
begin
  inc(t2); if t2 > t then begin next5 := 0; exit; end;

  next5 := last5;

  rez := 1;
  for i := 1 to l2+1 do
  begin
    b[i] := b[i] + rez; rez := 0;
    if b[i] = 2 then
    begin
      b[i] := 0;
      rez := 1;
    end;

    if b[i] = 1 then
      next5 := next5 + r5[i]
    else
      next5 := next5 - r5[i];

    if rez = 0 then break;
  end;

  if b[l2+1] = 1 then inc(l2);

  last5 := next5;
end;

begin
  assign(input,'puteri35.in'); reset(input);
  assign(output,'puteri35.out'); rewrite(output);
  settextbuf(output,bufout);

  readln(t);
  r3[1] := 1; r5[1] := 1;  a[1] := 0; b[1] := 0; last3 := 0; last5 := 0;
  for i := 2 to 30 do
  begin
    r3[i] := 3*r3[i-1];
    r5[i] := 5*r5[i-1];
    a[i] := 0; b[i] := 0;
  end;

  t1 := 0; t2 := 0; sum1 := 0; sum2 := 0; l1 := 0; l2 := 0;

  for ti := 1 to 2*t do
  begin
    if sum1 = 0 then sum1 := next3;
    if sum2 = 0 then sum2 := next5;

    if sum1 = 0 then
    begin
      sum := sum2;
      sum2 := 0;
    end
    else
    if sum2 = 0 then
    begin
      sum := sum1;
      sum1 := 0;
    end
    else
    if sum1 < sum2 then
    begin
      sum := sum1;
      sum1 := 0;
    end
    else
    begin
      sum := sum2;
      sum2 := 0;
    end;

    writeln(sum);
  end;



  close(input);
  close(output);
end.
