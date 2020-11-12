
const axios = require('axios')
const cheerio = require('cheerio')

const query = encodeURI("배방고등학교 급식")

axios.get(`https://search.naver.com/search.naver?query=${query}`).then(r =>{
    const $ = cheerio.load(r.data)
    let menu = []
    menuList = $('div.school_menu').children().children('li.menu_info').each((i,elem)=>{
        menu[i] = {}
        menu[i].date = $(elem).children('strong').text().split('[')[0]
        menu[i].list = $(elem).children('ul').children('li').map((i, elem)=>{
            return $(elem).text().replace(/\**[0-9.]+/i,'')
        }).get()
    })

    console.log(menu.reduce((acc, cur, idx, arr)=> `${acc}\n${cur.date}\n${cur.list.join('\n')}\n`, ''))
    
}).catch(e => {
    console.log(e)
})