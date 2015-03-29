var s,sact,cet:longint;
    put:longint;

begin
  assign(input,'taxe.in'); reset(input);
  assign(output,'taxe.out'); rewrite(output);

  readln(s); s := s div 4; cet := 0;

  repeat
    put := 1; sact := 1;
    while sact + put*4 <= s do
    begin
      put := 4*put;
      sact := sact + put;
    end;

    s := s - sact;
    cet := cet + put;

  until s = 0;

  write(cet);

  close(input);
  close(output);
end.
