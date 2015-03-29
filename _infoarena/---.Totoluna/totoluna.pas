const max = 1000500;
      modd = 666013; /// <<<<---- citeste cerinta inainte sa faci problema!!

var q,qi:longint;
    n,count,put,putmax:int64;
    i,k,cont,pcont,s,d:longint;
    ciur:array[0..max+5]of boolean;
    pr:array[0..max+5]of longint;
    nr:array[0..max+5]of int64;
    a:array[0..1,0..60]of int64;
    bufin,bufout:array[1..65000]of byte;

procedure initializeaza(); inline;
var i,j,h,t:longint;
begin
  for i := 1 to max do ciur[i] := true;
  cont := 0; h := trunc(sqrt(max));
  for i := 2 to h do
  begin
    if ciur[i] then
    begin
      t := max div i;
      for j := i to t do ciur[i*j] := false;
    end;
  end;

  for i := 2 to max do
    if ciur[i] then
    begin
      inc(cont); pr[cont] := i;
    end;
end;

procedure cauta(n,k:longint); inline;
var i,j:longint;
begin
  s := 0; d := 1;
  for i := 0 to n do a[d,i] := 1;

  for i := 2 to k do
  begin
    s := s xor 1; d := d xor 1;
    a[d,0] := 1;
    for j := 1 to n do a[d,j] := (a[d,j-1] + a[s,j])mod modd;
  end;
end;

begin
  assign(input,'totoluna.in'); reset(input);
  assign(output,'totoluna.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  initializeaza;

  readln(q);
  for qi := 1 to q do
  begin
    readln(n,k);
    put := 1 shl k;
    if n mod put = 0 then
    begin
      n := n div put;
      pcont := 0;   putmax := 1;

      for i := 1 to cont do
      begin
        if n mod pr[i] = 0 then
        begin
          inc(pcont);  put := 0;
          while n mod pr[i] = 0 do
          begin
            inc(put);
            n := n div pr[i];
          end;
          nr[pcont] := put;
          if put > putmax then  putmax := put;
        end;

        if n = 1 then break;
      end;
      if n <> 1 then
      begin
        inc(pcont);
        nr[pcont] := 1;
      end;
      /////////am descoperit divizorii si puterile lor
      count := 1;

      cauta(putmax,k);
      for i := 1 to pcont do
      begin
        count := (count * a[d,nr[i]])mod modd;
      end;

      writeln(count);
    end
    else
      writeln(0);
  end;



  close(input);
  close(output);
end.
