var t,ti:longint;
    per,lim:int64;
    rez,n,v:int64;
    bufin,bufout:array[1..65000]of byte;

begin
  assign(input,'progresii2.in'); reset(input);
  assign(output,'progresii2.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(t);
  for ti := 1 to t do
  begin
    readln(v,n);

    if n = 1 then begin rez := v; end else
    begin

      dec(v); dec(n); rez := 0;
      per := v div n;
      lim := n * per;
      rez := rez + (v-lim+1)*per;
      v := lim-1;

      per := v div n;
      rez := rez + n*((per*(per+1))div 2);

    end;

    writeln(rez);
  end;


  close(input);
  close(output);
end.
