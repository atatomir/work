var t,ti,last,n,i,q:longint;
    s:ansistring;
    pr:array[0..1000005]of longint;
    bufin:array[1..65000]of byte;

begin
  assign(input,'prefix.in'); reset(input);
  assign(output,'prefix.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(t);
  for ti := 1 to t do
  begin
    readln(s); n := length(s);
    pr[1] := 0; q := 0; last := 0;

    for i := 2 to n do
    begin
      while (q>0)and(s[q+1]<>s[i]) do q := pr[q];
      if s[q+1] = s[i] then inc(q);
      pr[i] := q;
    end;
    for i := n downto 1 do
    begin
      if (pr[i]<>0)and(i mod( i - pr[i])=0) then
      begin
        last := i;
        break;
      end;
    end;

    writeln(last);
  end;


  close(input);
  close(output);
end.
