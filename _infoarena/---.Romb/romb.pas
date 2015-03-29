var t,ti,i,k:longint;
    dx,dy,cx,cy:real;
    alfa,beta:real;
    cod:int64;

begin
  assign(input,'romb.in'); reset(input);
  assign(output,'romb.out'); rewrite(output);

  readln(t);

  for ti := 1 to t do
  begin
    readln(dx,dy,k,cx,cy);
    cod := 1;

    for i := 1 to k do
    begin
      if cx > 0 then
      begin
        if cy > 0 then
        begin              //pos 1 si 4
          alfa := dy / dx;
          beta := cy / cx;
          if alfa < beta then
          begin                                     {1}
            dx := dx/2; dy := dy/2;
            cy := cy - dy ;
            cod := cod * 4 - 3;
          end
          else
          begin                                      {4}
            dx := dx/2; dy := dy/2;
            cx := cx - dx;
            cod := cod * 4;
          end;
        end
        else
        begin              //pos 3 si 4
          alfa :=  dy / dx;
          beta := -cy / cx;
          if alfa > beta then
          begin                                      {4}
            dx := dx/2; dy := dy/2;
            cx := cx - dx;
            cod := cod * 4;
          end
          else
          begin                                      {3}
            dx := dx/2; dy := dy/2;
            cy := cy + dy;
            cod := cod * 4 - 1;
          end;
        end;
      end
      else
      begin
        if cy > 0 then
        begin               //pos 1 si 2
          alfa :=  dy / dx;
          if (cx = 0) then beta := 999999999999
          else
             beta := -cy / cx;
          if alfa < beta then
          begin                                       {1}
            dx := dx/2; dy := dy/2;
            cy := cy - dy ;
            cod  := cod * 4 - 3;
          end
          else
          begin                                       {2}
            dx := dx/2; dy := dy/2;
            cx := cx + dx;
            cod := cod * 4 - 2;
          end;
        end
        else
        begin               //pos 2 si 3
          alfa := dy / dx;
          if (cx = 0) then beta := 999999999999
          else
            beta := cy / cx;
          if alfa > beta then
          begin                                        {2}

            dx := dx/2; dy := dy/2;
            cx := cx + dx;
            cod := cod * 4 - 2;
          end
          else
          begin                                        {3}

            dx := dx/2; dy := dy/2;
            cy := cy + dy;
            cod := cod * 4 - 1;
          end;
        end;
      end;


    end;

    writeln(cod);

  end;


  close(input);
  close(output);
end.
