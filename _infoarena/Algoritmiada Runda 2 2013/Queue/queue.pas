var n:longint;
    a:array[1..30000]of string;
    s:string;
    i,s1i,s1f,s2i,s2f,h,j:longint;
    bufin,bufout:array[1..65000]of byte;
 
begin
  assign(input,'queue.in'); reset(input);
  assign(output,'queue.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);
 
  readln(n); s1i := 0; s1f:=0; s2i:= 0; s2f:= 0;
  for i := 1 to n do
  begin
    readln(s);
    if s[2]= 'u' then
    begin
      inc(s1f);
      if s1i = 0 then s1i := s1f;
      h := length(s)-1;
      a[s1f] := '';
      for j := 11 to h do
        a[s1f] := a[s1f] + s[j];
      writeln(i,': read(',a[s1f],') push(1,',a[s1f],')');
    end
    else
    begin
      write(i,': ');
 
      if s2i= 0 then
      begin
        for j := s1f downto s1i do
        begin
          write('pop(1) push(2,',a[j],') ') ;
        end;
        s2i := s1i;
        s2f := s1f;
        s1i := 0;
      end;
 
      writeln('pop(2) write(',a[s2i],')');
      s2i := s2i + 1;
      if s2i > s2f then s2i := 0;
    end;
  end;
 
  close(input);
  close(output);
end.
end.