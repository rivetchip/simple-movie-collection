
import { h, app as hyperapp } from '../hyperapp'



export const SearchToolbar = ({ onSearch }) => (

    <search-toolbar>
        <input
            onkeyup={e => onSearch(e, e.target.value)}
            class="search-input"
            type="search"
            placeholder="Recherche"
        />
    </search-toolbar>

)

export const ProductItems = ({products, onProductClick, onProductFavorite}) => (

    <product-items>
    {
        products.map((product, index) => (
            <ProductItem
                index={index}
                title={product.title}
                favorite={product.favorite}
                onClick={onProductClick}
                onFavorite={onProductFavorite}
            />
        ))
    }
    </product-items>

)

export const ProductItem = ({ index, title, favorite, onClick, onFavorite, hidden = false }) => (

    <product-item
        class={hidden && "is-hidden"}
        onclick={e => onClick(e, index)}
    >
        <div class="title">{title}</div>

        { favorite && (
            <div
                class="favorite"
                onclick={e => onFavorite(e, index)}
            >
            </div>
        )}

    </product-item>
)

