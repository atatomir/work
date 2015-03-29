program interzis;

type marray=array[1..15000]of byte;

var a:marray;
    n,l,i,j,k:longint;
    ls:array[1..1000]of byte;
    f,fo:text;
    c:char;
    nr:longint;
    gasit:boolean;

function genereaza(var x:marray):boolean;
begin
  genereaza := true;
  if x[n] = 0 then x[n] := 1 else x[n] := 0;

  for i := n-1 downto 1 do
  begin
    if x[i+1] = 0 then
    begin
      if x[i] = 0 then begin x[i] := 1;break;  end else
      begin
        x[i] := 0;
        if i=1 then genereaza := false;
      end;
    end
    else
      break;
  end;



end;

function cauta(x:marray;pos:longint):boolean;
begin
  cauta := true;
  for j := pos+1 to pos + l-1 do
  begin
    if x[j] <> ls[j-pos] then
    begin
      cauta := false;
      break;
    end;
  end;
end;


begin
  nr :=0;
  assign(f,'interzis.in'); reset(f);
  readln(f,n,l);
  for i := 1 to l do
  begin
    read(f,c);
    if c = 'a' then ls[i] := 0
    else            ls[i] := 1;
  end;
  for i := 1 to n do
    a[i] := 0;
/////////////////////initializeaza date
  if l < n then
  repeat
    gasit := false;
    for k := 1 to n-l+1 do
      if a[k] = ls[1] then
      begin
        if cauta(a,k)= true then
        begin
          gasit := true;
          break;
        end;
      end;

    if gasit = false then
    begin
      inc(nr);
      nr := nr mod 101267
    end;
  until genereaza(a) = false
  else
  begin
    nr := 1;
    for k := 1 to n do
      nr := (nr *2) mod 101267;
    if l = n then nr := nr -1 ;
  end;
///////////////////////procedura cauta
  assign(fo,'interzis.out'); rewrite(fo);
  write(fo,nr);
  close(fo);
end.
