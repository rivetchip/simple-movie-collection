/** @jsx h */
'use strict';

import { h, app as hyperapp } from './hyperapp'

// components
import {AppTitlebar} from './components/app-titlebar'
import {AppToolbar} from './components/app-toolbar'

import {SearchToolbar, ProductItems} from './components/app-sidebar'

import {AppStatusbar} from './components/app-statusbar'

console.log(process);



/*
fetch('moviesapi://tmdb-fr/movie/78')
// fetch('moviesapi://tmdb-fr/search/blade runner')
.then(response => response.text())

.then(function(response) {
    console.log(response)
})
*/

// previewPanel index
// send('get-product', productIndex)

/*
if( previousSelectedProduct ) {
            previousSelectedProduct.classList.remove('is-selected')
        }
*/

//openProductDisplay







const state = { // initial state
    fullscreen: false,
    location: 'idle', // current publicatoion or preview mode

    titlebar: {
        title: 'Movie Collection'
    },

    providerIndex: 1, // french
    providers: [
        { name: 'TMDb', identifier: 'tmdb', lang: 'en' },
        { name: 'TMDb', identifier: 'tmdb', lang: 'fr' },
    ],

    productIndex: null, // current select product
    products: new Map([
        [4, {title:'sqd', favorite: false}],
        [5, {title:'sqerd', favorite: true}],
        [6, {title:'sqd', favorite: false}],
        [7, {title:'sqerd', favorite: true}],
    ])
}

var actions = {

    titlebar: {

        onClose: ({event}) => {
            return send('application-close')
        },
    
        onMinimize: ({event}) => {
            return send('application-minimize')
        },
    
        onMaximize: ({event}) => {
            return send('application-maximize')
        }
    },

    toolbar: {

        // open file button
        onOpen: ({event}) => {
            return send('open-collection-dialog')
        },

        // save file button
        onSave: ({event}) => {
            return send('save-collection-dialog')
        },

        // create new product button
        onNew: ({event}) => {

        },
    },

    // when user click fullscreen on the main app
    onFullscreen: ({status}) => {
        return {fullscreen: status}
    },

    // radio provider change
    onProviderChange: ({event, index}) => {
        return {providerIndex: index}
    },

    // when the collection has been opened
    onReceiveCollection: ({products}) => {
        return {products: new Map(
            products.map((product, index) => [index, product]
        ))}
    },













    onProductClick: ({event, index}) => (state, actions) => {
        console.log('onProductClick', index)
        // console.log(index)


        //return fetch('moviesapi://tmdb-fr/movie/78')
        // return fetch('moviesapi://tmdb-fr/search/blade runner')
        // .then(response => response.json())
        // .then(actions.setQuotes);

        // open the preview ; then set the selected

        return {productIndex: index}
    },

    // search event when using the search box on the sidebar

    onSearch: ({event, keyword, keyCode}) => ({products}, actions) => {

        // set to lower case in case of search accents and others
        keyword = keyword.toLowerCase()

        // if escape : show all products
        let showEverything = false

        if( keyCode == 'Escape' ) {
            showEverything = true
        }

        // hide all products based on keyword ; or if escape : show the all

        products.forEach((product, index) => {
            let {title} = product
            title = title.toLowerCase()

            product.hidden = showEverything ? false : title.indexOf(keyword) < 0

            products.set(index, product)
        })

        return {products}
    },
    
    onProductFavorite: ({event, index}) => ({products}, actions) => {

        console.log('favorite')
        console.log(event)
        console.log(index)
        // console.log(actions)

        // products.push({ // TODO
        //     title: 'qsd'
        // })

        return {products}
    },
};





const view = (state, actions) => (

    <app className={['viewport', state.fullscreen && 'is-fullscreen'].filter(c => !!c).join(' ')}>

        <AppTitlebar
            {...state.titlebar}
            events={actions.titlebar}
            // TODO BETTER
        />

        <AppToolbar
            providerIndex={state.providerIndex}
            providers={state.providers}
            onProviderChange={actions.onProviderChange}
            events={actions.toolbar}
        />

        <app-layout>

            <app-sidebar>

                <SearchToolbar
                    onSearch={actions.onSearch}
                />
                <ProductItems
                    productIndex={state.productIndex}
                    products={state.products}
                    onProductClick={actions.onProductClick}
                    onProductFavorite={actions.onProductFavorite}
                />

            </app-sidebar>


            {/* EDITION */}





        </app-layout>

        <AppStatusbar
            productCount={state.products.size}
        />

    </app>
)



const app = hyperapp(state, actions, view, document.body)



// events

receive('fullscreen-status-changed', (event, status) => {
    return app.onFullscreen({status})
})

// receive a notification from the main app
receive('notification', (event, message) => {
    //createSnackbar(viewport, message)
})

// get the full collection from server
receive('get-collection', (event, products) => {
    return app.onReceiveCollection({products})
})

// get a single, full product
receive('get-product', (event, index, product) => {
    // parse and show the view panel
    if( product ) {
        // winState = 'preview'

    }
})





const updateOnlineStatus = (event) => {
    return send('online-status-changed', navigator.onLine ? 'online' : 'offline')
}

addEventListener('online',  updateOnlineStatus)
addEventListener('offline', updateOnlineStatus)











document.addEventListener('DOMContentLoaded', () => {

})