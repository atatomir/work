const base = 17;
      modd = 1000007;
var n,i,rez,h,nn,j,p:longint;
    s:ansistring;
    sb:array[0..10000005]of byte;
    bufin:array[1..65000]of byte;
    ok:array[0..5000005]of byte;

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


begin
  assign(input,'perioada2.in'); reset(input);
  assign(output,'perioada2.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n);
  readln(s);
  for i := 1 to n do sb[i] := ord(s[i]);
  s := '';

  nn := n div 2;
  for i := 1 to nn do ok[i] := 0;

  for i := 1 to nn do
  begin
    if ok[i] = 0 then
    begin
      if verif(i) then
      begin
        h := nn div i; p := i;
        for j := 2 to h do
        begin
          p := p + i;
          ok[p] := 1;
        end;
      end;
    end;
  end;

  rez := 0;
  for i := 1 to nn do rez := rez + ok[i];
  writeln(rez);

  close(input);
  close(output);
end.
