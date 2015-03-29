type divizor = record
       dv,r,sum:longint;
     end;
const base = 17;
      modd = 1000007;
var n,nn,i,h,cont,rez:longint;
    s:ansistring;
    sb:array[0..10000005]of byte;
    bufin:array[1..65000]of byte;
    d:array[0..10]of divizor;

function verif(l:longint):boolean;
var phash,hash,ind,h,bg,en:int64;
    i,j:longint;
begin
  verif := true;
  phash := 1; ind := 1;
  for i := 1 to l do
  begin
    phash := (phash + sb[i]*ind) mod modd;
    ind := (ind * base)mod modd;
  end;

  h := n div l;
  for i := 2 to h do
  begin
    bg := l*(i-1)+1; en := l*i;
    hash := 1; ind := 1;
    for j := bg to en do
    begin
      hash := (hash + sb[j]*ind) mod modd;
      ind := (ind*base)mod modd;
    end;
    if hash <> phash then
    begin
      verif := false;
      break;
    end;
  end;

end;

procedure Rezolva(pas,act:longint);
var i:longint;
begin
  for i := 0 to d[pas].r do
  begin
    if verif(act) then
    begin
      rez := rez + d[pas+1].sum*(d[pas].r-i+1) - 1;
      exit;
    end
    else
      Rezolva(pas+1,act);
    act := act * d[pas].dv;
  end;
end;

begin
  assign(input,'perioada2.in'); reset(input);
  assign(output,'perioada2.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n);
  readln(s);
  for i := 1 to n do sb[i] := ord(s[i]);

  cont := 0; nn := n; h := trunc(sqrt(nn))+1;
  for i := 2 to h do
  begin
    if nn mod i = 0 then
    begin
      inc(cont);
      d[cont].dv := i; d[cont].r := 0;
      while nn mod i = 0 do
      begin
        inc(d[cont].r);
        nn := nn div i;
      end;
    end;
  end;
  if nn <> 1 then
  begin
    inc(cont);
    d[cont].r := 1; d[cont].dv := nn;
  end;

  d[cont].sum := d[cont].r;
  for i := cont-1 downto 1 do
    d[i].sum := d[i].r * d[i+1].sum;

  rez := 0; d[cont+1].sum := 1;
  Rezolva(1,1);
  writeln(rez);

  close(input);
  close(output);
end.