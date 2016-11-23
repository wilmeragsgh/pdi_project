ui <- shinyUI(
    fluidPage(
        tags$head(
            tags$style(
                HTML("
                    @import url('//fonts.googleapis.com/css?family=Lobster|Cabin:400,700');
                    .shiny-text-output {
                      background-color:#fff;
                    }
                    .table.data{
                    width: 100%;
                    }
                    #image1 #image2{
                     max-height: 540px;
                     height: 100% !important;
                     width: 100%;
                    }
                    #loadHist{
                     margin-top: 4%;
                    }
                    #reloadHist{
                     margin-top: 4%;
                    }
                    #button{
                     horizontal-align: middle;
                    }
                    img{
                     display: block !important;
                     margin: 0 auto !important;
                    }")
                )
            ),
        h1(span("One-cut Grabcut", 
            style = "font-weight: 300; font-family: 'Lobster', cursive;"
            ), 
            style = "font-family: 'Source Sans Pro';
                color: #fff; text-align: center;
                background-image: url('texturebg.png');
                padding: 1%"
           ),
        fluidRow(
            column(
                       width=3,
                       style = 'align: center; text-align: center',
                       wellPanel(fileInput(inputId = 'files', 
                           label = 'Select an Image',
                           accept=c('image/bmp', 'image/png','image/jpg','.bmp','.jpg','.png')
                           ),
                       actionButton('reloadInput',
                                    'Reload image',
                                    icon = icon('refresh'))),
                       hr(),
                       actionButton('combine',
                                    'Combine fg/bg',
                                    icon = icon('magic')),
                       h4('Transformations',style = 'font-weight: 700; text-align: center'),
                       radioButtons("source", label = "on:",
                                    choices = list("O" = 1, "F" = 2, "B" = 3),inline = T, 
                                    selected = 1),
                       wellPanel(h5('Negative:',
                                               style = 'font-weight: 700; text-align: center'
                                            ),
                                            actionButton(
                                                'negativeT',
                                                'Go!',
                                                icon = icon('adjust')
                                            ),
                                            hr(),
                                             sliderInput("slider2",label = 'Umbralization:' ,min = 0, max = 255, 
                                                         value = c(0, 255)),
                                             actionButton(
                                             'umbralizationI',
                                             'Go!',
                                             icon = icon('bars')
                                             ),
                                             hr(),
                                            sliderInput(
                                                "bright", 
                                                "Brightness:",
                                                min=-255, 
                                                max=255, 
                                                value=0,
                                                step = 1
                                 )
                                 ),
                       hr(),
                       h6('Save to ./output.bmp:',
                          style = 'font-weight: 700; text-align: center'
                       ),
                           actionButton('exportImage',
                                      '',
                                      icon = icon('archive'),width = "30%")
                   ),
                   column(width = 9, 
                          tabsetPanel(
                              tabPanel('Original',
                                       uiOutput('images', 
                                                style = 'overflow:auto; align:center',container = tags$div),
                                       hr(),
                                       actionButton('grabcutB', 'select foreground',style = "text-align: center; width:100%")),
                                       #actionButton("grabcutB","select foreground",style = 'font-weight: 700; text-align: center')),
                              tabPanel('Foreground',
                                       uiOutput('images2', 
                                                style = 'overflow:auto; align:center',container = tags$div)),
                              tabPanel('Background',
                                       uiOutput('images3', 
                                                style = 'overflow:auto; align:center',container = tags$div)),
                              tabPanel('Result',
                                       uiOutput('images4', 
                                                style = 'overflow:auto; align:center',container = tags$div))
                              )
                          )
            )
    )
)