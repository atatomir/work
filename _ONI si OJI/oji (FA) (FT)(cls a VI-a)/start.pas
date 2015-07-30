var n,s:word;
    c,ch:byte;

procedure citire;
var f :text;
begin
  assign(f,'file.in');
  reset(f);
  readln(f,n,c);
  close(f);
end;

procedure scriere;
var fo:text;
begin
  assign(fo,'file.out');
  rewrite(fo);
  write(fo,s);
  close(fo);
end;

begin
  citire;
  s := 0;

  case n of
    1..9: if n > c-1 then s := 1;
    10..99: begin
              s := s + (n div 10);
              if n div 10 > c then s := s + 10;
              if n div 10 = c then s := s + (n mod 10) +1;
              n := n mod 10;
              //terminat zecile;
              if n mod 10 > c-1 then inc(s);
              //terminat unitatile;
            end;
    100..999: begin
                s := s + 20*(n div 100);
                if n div 100 > c then s := s + 100;
                if n div 100 = c then s := s + (n mod 100) +1;
                n := n mod 100;
                // terminat sutele
                s := s + (n div 10);
                if n div 10 > c then s := s + 10;
                if n div 10 = c then s := s + (n mod 10) +1;
                n := n mod 10;
                //terminat zecile;
                if n mod 10 > c-1 then inc(s);
                //terminat unitatile;
              end;
    1000..9999:begin
                 s := s+ 300*(n div 1000);
                 if n div 1000 > c then s := s + 1000;
                 if n div 1000 = c then s := s + (n div 1000) + 1;
                 n := n mod 1000;
                 // terminat miile
                 s := s + 20*(n div 100);
                 if n div 100 > c then s := s + 100;
                 if n div 100 = c then s := s + (n mod 100) +1;
                 n := n mod 100;
                 // terminat sutele
                 s := s + (n div 10);
                 if n div 10 > c then s := s + 10;
                 if n div 10 = c then s := s + (n mod 10) +1;
                 n := n mod 10;
                 //terminat zecile;
                 if n mod 10 > c-1 then inc(s);
                 //terminat unitatile;
               end;
    10000..99999: begin
                    s := s + 4000*(n div 10000);
                    if n div 10000 > c then s := s + 10000;
                    if n div 10000 = c then s := s + ( n div 10000) +1;
                    n := n mod 10000;
                    //terminat zeciledemii;
                    s := s+ 300*(n div 1000);
                    if n div 1000 > c then s := s + 1000;
                    if n div 1000 = c then s := s + (n div 1000) + 1;
                    n := n mod 1000;
                    // terminat miile
                    s := s + 20*(n div 100);
                    if n div 100 > c then s := s + 100;
                    if n div 100 = c then s := s + (n mod 100) +1;
                    n := n mod 100;
                    // terminat sutele
                    s := s + (n div 10);
                    if n div 10 > c then s := s + 10;
                    if n div 10 = c then s := s + (n mod 10) +1;
                    n := n mod 10;
                    //terminat zecile;
                    if n mod 10 > c-1 then inc(s);
                    //terminat unitatile;
                  end;
  end;



  scriere;
end.
