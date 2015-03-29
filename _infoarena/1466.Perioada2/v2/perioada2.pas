const base = 17;
      modd = 1000007;
var n,i,rez:longint;
    s:ansistring;
    sb:array[0..10000005]of byte;
    bufin:array[1..65000]of byte;
    ok:array[0..5000005]of byte;

function verif(l,n:longint):boolean;
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

procedure Rezolva(n:longint);
var i,h:longint;
begin
  h := n div 2;
  for i := h downto 1 do
  begin
    if n mod i = 0 then
    begin
      if ok[i] = 0 then
      begin
        if verif(i,n) then
        begin
          ok[i] := 1; inc(rez);
          Rezolva(n div i);
        end
        else
          ok[i] := -1;
      end;
    end;
  end;

end;

begin
  assign(input,'perioada2.in'); reset(input);
  assign(output,'perioada2.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n);
  readln(s);
  for i := 1 to n do sb[i] := ord(s[i]);
  s := '';

  for i := 1 to (n div 2) do ok[i] := 0;

  rez := 0;
  Rezolva(n);
  writeln(rez);

  close(input);
  close(output);
end.
