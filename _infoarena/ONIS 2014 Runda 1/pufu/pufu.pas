var t,ti,n,i:Longint;
    a:array[1..2]of shortint;
    s:string;

begin
  assign(input,'pufu.in'); reset(input);
  assign(output,'pufu.out'); rewrite(output);

  readln(t);
  for ti := 1 to t do
  begin
    readln(n); a[1] := 0; a[2] := 0;
    for i := 1 to n do
    begin
      readln(s);
      case s[3] of
        'o':inc(a[1]);
        's':inc(a[2]);
      end;
    end;
    writeln(a[1],' ',a[2],' ',n-a[1]-a[2]);
  end;


  close(input);
  close(output);
end.