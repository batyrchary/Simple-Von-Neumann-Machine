import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.Set;

public class Main {

    public static BufferedReader br2 = null;
    public static FileReader fr2 = null;
    public static ArrayList<Integer[]> edges=new ArrayList<>();
    public static ArrayList<Integer> nodes=new ArrayList<>();
    public static ArrayList<ArrayList<Float>>similarities =new ArrayList<>();

    public static ArrayList<Integer> dem=new ArrayList<>();
    public static ArrayList<Integer> gop=new ArrayList<>();

    public static ArrayList<Float> gop_center=new ArrayList<>();
    public static ArrayList<Float> dem_center=new ArrayList<>();



    public static float distance(ArrayList<Float> center, ArrayList<Float> item)
    {
        float accumaltor=0;
        for(int i=0; i<center.size(); i++)
        {
            float c=center.get(i);
            float it=item.get(i);
            accumaltor=accumaltor+(c-it)*(c-it);
        }

        return (float) Math.sqrt(accumaltor);
    }

    public static  boolean centerCalculator()
    {
        boolean flag=false;
        ArrayList<Float> newgopCenter=new ArrayList<>();
        ArrayList<Float> newdemCenter=new ArrayList<>();

        for(int i=0; i<nodes.size();i++)
        {
            newgopCenter.add(0.f);
            newdemCenter.add(0.f);
        }


        for(int i=0; i<gop.size(); i++)
        {
            int index=gop.get(i);
            ArrayList<Float> row=similarities.get(index);
            for(int j=0; j<row.size();j++)
            {
                newgopCenter.set(j,newgopCenter.get(j)+row.get(j));
            }
        }
        for(int i=0; i<dem.size(); i++)
        {
            int index=dem.get(i);
            ArrayList<Float> row=similarities.get(index);
            for(int j=0; j<row.size();j++)
            {
                newdemCenter.set(j,newdemCenter.get(j)+row.get(j));
            }
        }
        int gopsize=gop.size();
        int demsize=dem.size();
        for(int i=0; i<similarities.size();i++)
        {

            float ng=newgopCenter.get(i)/gopsize;
            float nd=newdemCenter.get(i)/demsize;

            if(ng!=gop_center.get(i) || nd != dem_center.get(i))
                flag=true;
            gop_center.set(i,ng);
            dem_center.set(i,nd);

        }

        return flag;

    }

    public static void Kmean()
    {
        gop_center=similarities.get(0);
        dem_center=similarities.get(similarities.size()-1);

        int len=similarities.size();
        for(int i=0; i<len; i++)
        {
            ArrayList<Float> item=similarities.get(i);

            float d1=distance(gop_center,item);
            float d2=distance(dem_center,item);

            if(d1<d2)
            {
                gop.add(i);
            }
            else
            {
                dem.add(i);
            }
        }

        boolean flag=true;
        while(flag)
        {
            flag=centerCalculator();

            gop.clear();
            dem.clear();
            for(int i=0; i<len; i++)
            {
                ArrayList<Float> item=similarities.get(i);

                float d1=distance(gop_center,item);
                float d2=distance(dem_center,item);

                if(d1<d2)
                {
                    gop.add(i);
                }
                else
                {
                    dem.add(i);
                }
            }
        }

        for(int i=0; i<gop.size(); i++)
        {
            System.out.println(gop.get(i)+" 0");
        }
        for(int i=0; i<dem.size(); i++)
        {
            System.out.println(dem.get(i)+" 1");
        }
     //   System.out.println("gopsize="+gop.size());
       // System.out.println("demsize="+dem.size());

    }



    public static float jaccardCalculator(int s, int t)
    {
        float intersection=0;
        float union=0;


        int len=edges.size();
        ArrayList<Integer> sneighbors=new ArrayList<>();
        ArrayList<Integer> tneighbors=new ArrayList<>();
        ArrayList<Integer> unionList=new ArrayList<>();
        ArrayList<Integer> intersectionList=new ArrayList<>();

        for(int i=0;i<len;i++)
        {
            Integer[] tuple=edges.get(i);
            if(tuple[0]==s)
            {
                sneighbors.add(tuple[1]);
            }
            else if(tuple[1]==s)
            {
                sneighbors.add(tuple[0]);
            }

            if(tuple[0]==t)
            {
                tneighbors.add(tuple[1]);
            }
            else if(tuple[1]==t)
            {
                tneighbors.add(tuple[0]);
            }
        }

        for(int i=0; i<sneighbors.size(); i++)
        {
            int item=sneighbors.get(i);
            if(tneighbors.indexOf(item)!=-1)
            {
                intersectionList.add(item);
            }
            unionList.add(item);
        }
        for(int i=0; i<tneighbors.size(); i++)
        {
            int item=tneighbors.get(i);
            if(unionList.indexOf(item)==-1)
            {
                unionList.add(item);
            }
        }

        union=unionList.size();
        intersection=intersectionList.size();
//        System.out.println("intersection="+intersection);
  //      System.out.println("union="+union);

        return intersection/union;


    }

    public static void similaritycreator()
    {
        int len=nodes.size();
        for(int i=0; i<len; i++)
        {
            ArrayList<Float> row=new ArrayList<>();
            for(int j=0; j<len; j++)
            {
                int s=nodes.get(i);
                int t=nodes.get(j);

                float jaccard=jaccardCalculator(s,t);
                //System.out.println(jaccard);

                row.add(jaccard);
            }
            similarities.add(row);
        }
    }

    public static void reader(filename) {

        try
        {

            fr2 = new FileReader(filename);
            br2 = new BufferedReader(fr2);

            String line;
            while ((line = br2.readLine()) != null) {

                Integer source=Integer.parseInt(line.split(",")[0]);
                Integer target=Integer.parseInt(line.split(",")[1]);

                Integer edge[]={source,target};

                if(nodes.indexOf(source)==-1)
                    nodes.add(source);
                if(nodes.indexOf(target)==-1)
                    nodes.add(target);

                edges.add(edge);

              //  System.out.println(line);
            }

            Collections.sort(nodes.subList(1, nodes.size()));
          //  for(int i=0; i<nodes.size(); i++)
            //    System.out.println(nodes.get(i));

         //   System.out.println(nodes.size());
        } catch (IOException e) {
            // do something
        }
    }



    public static void main(String args[])
    {
        reader(args[0]);
        similaritycreator();
        Kmean();
    }


};