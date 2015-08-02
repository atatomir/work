var bufin,bufout:array[1..65000]of byte;
    n,i,t,h:longint;
    a:array[1..500001]of longint;
    ok:boolean;

begin
  assign(input,'algsort.in'); reset(input);
  assign(output,'algsort.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(n);
  for i := 1 to n do read(a[i]); h := n;

  repeat
    ok := true;
    h := h -1;
    for i := 1 to h do
      if a[i] > a[i+1] then
      begin
        t := a[i];
        a[i]:=a[i+1];
        a[i+1] := t;
        ok := false;
      end;
  until ok = true;

  for i := 1 to n do write(a[i],' ');



  close(input);
  close(output);
end.