/* A simple c Program to implement API using Libvirt */

#include <stdio.h>
#include <stdlib.h>
#include <libvirt/libvirt.h>

void main()
{

    int i,val=-1,choice,choice_id,num_domains;
    int *active_domains;
    virConnectPtr conn;
    virDomainPtr vdp;

    conn = virConnectOpen("xen:///");

    if (conn == NULL) {
        fprintf(stderr, "Problem opening connection to XEN:///  \n");
        return 1;
    }
    else
    {

        //num_domians determine how large to make the ID array, the application can use the API call virConnectNumOfDomains.
        num_domains=virConnectNumOfDomains(conn);
        active_domanins=malloc(sizeof(int) * num_domains);
        //virConnectListDomains, requires the caller to pass in a pre-allocated int array which will be filled in domain IDs.
        num_domains = virConnectListDomains(conn, active_domains, num_domains);

        printf("Active domain IDs : \n");
        for (i = 0 ; i < num_domains ; i++) {
            printf("  %d\n", active_domains[i]);
        }
        free(active_domains);

        printf("1.Start\n2.Suspend\n3.Resume\n4.stop\n5.exit");
        scanf("%d",&choice);

        printf("\n Please Insert the Active Domian ID ");
        scanf("%d",&choice_id);

        vdp=virDomainLookupById(conn,choice_id);

        while(1)
        {
            switch(choice)
            {
                case 1:val=virDomainCreate(vdp);/* Start */
                       if(val==0)      
                           printf("Success");
                       else
                           printf("Failed");   
                       break;
                case 2:val=virDomainSuspend(vdp);/* Suspend */
                       if(val==0)
                           printf("Success");
                       else
                           printf("Failed");   
                       break;
                case 3: val=virDomainResume(vdp);/* Resume */
                        if(val==0)                     
                            printf("Success");
                        else
                            printf("Failed");   
                        break;

                case 4: val=virDomainStop(vdp);/* Stop */
                        if(val==0)                     
                            printf("Success");
                        else
                            printf("Failed");   
                        break;
                default:exit(1);
            }
        }
        virConnectClose(conn);
    }
}

