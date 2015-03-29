const modd = 100003;

var op,nr,est,i:longint;
    c:char;
    ciur:array[0..100005]of boolean;
    p,v:array[0..10000]of longint;
    rez:int64;

procedure do_ciur(); inline;
var i,h,j,t:longint;
begin
  for i := 2 to nr do ciur[i] := true;
  h := trunc(sqrt(nr));
  for i := 2 to h do
    if ciur[i] then
    begin
      t := nr div i;
      for j := i to t do ciur[i*j] := false;
    end;
  p[0] := 0;
  for i := 2 to nr do
  begin
    if ciur[i] then
    begin
      inc(p[0]); v[p[0]] := 0;
      p[p[0]] := i;
    end;
  end;
end;

procedure adauga(n,ind:longint); inline;
var i,nl:longint;
begin
  for i := 1 to p[0] do
  begin
    if n < p[0] then break;

    nl := n;
    while nl <> 0 do
    begin
      nl := nl div p[i];
      v[i] := v[i] + ind*nl;
    end;

  end;
end;

function pow(a,b:int64):int64;
begin
  pow := 1;
  while b <> 0 do
  begin
    if b and 1 = 1 then pow := (pow*a)mod modd;
    a := (a * a)mod modd;
    b := b shr 1;
  end;
end;

begin
  assign(input,'spion.in'); reset(input);
  assign(output,'spion.out'); rewrite(output);

  readln(op);
  nr := 0; est := 0;
  while not Eof do
  begin
   read(c);

   if not((c = 'V')or(c = 'E')) then break;

   inc(nr);
   if c = 'E' then inc(est);
  end;

  if op = 1 then
    writeln(est+1)
  else
  begin
    do_ciur();

    adauga(nr,1);
    adauga(nr-est,-1);
    adauga(est,-1);

    rez := 1;
    for i := 1 to p[0] do
      if v[i] > 0 then
      begin
        rez := (rez * pow(p[i],v[i])) mod modd;
      end;

    writeln(rez);
  end;


  close(input);
  close(output);
end.
